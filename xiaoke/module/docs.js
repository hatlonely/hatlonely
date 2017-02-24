var mysql = require('mysql');
var config = require('../config/xiaoke');
var cache = require('./cache');
var crypto = require('crypto');
var async = require('async');

function md5(text) {
    return crypto.createHash('md5').update(text, 'utf-8').digest('hex');
}

var select = function(doc) {
    async.waterfall([
        function(callback) {
            var connection = mysql.createConnection(config['mysql']);
            connection.connect(function(err) {
                if (err) {
                    connection.destroy();
                }
                callback(err, connection)
            });
        },
        function(connection, callback) {
            connection.query('SELECT * FROM docs WHERE md5=?', md5(doc), function(err, rows) {
                if (err) {
                    connection.destroy();
                }
                callback(err, {
                    'rows': rows,
                    'connection': connection
                })
            })
        },
        function(connrows, callback) {
            connection = connrows['connection']
            rows = connrows['rows']
            if (rows.length == 0) {
                cache['docs'][doc] = 1;
                connection.query('INSERT INTO docs (`title`, `md5`, `views`) VALUES (?, ?, 1)', [doc, md5(doc)], function(err, rows) {
                    callback(err, null);
                    connection.destroy();
                });
            } else {
                cache['docs'][doc] = rows[0].views + 1;
                connection.query('UPDATE docs SET views=views+1 WHERE md5=?', md5(doc), function(err, rows) {
                    callback(err, null);
                    connection.destroy();
                });
            }
        }
    ], function(err, result) {
        if (err) {
            console.error(err);
        }
    });
}

var DocsModule = {
    'select': select,
}

module.exports = DocsModule;
