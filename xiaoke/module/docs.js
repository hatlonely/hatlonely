var mysql = require('mysql');
var config = require('../config/xiaoke');
var cache = require('./cache');
var crypto = require('crypto');

function md5(text) {
    return crypto.createHash('md5').update(text, 'utf-8').digest('hex');
}

var select = function(doc) {
    var connection = mysql.createConnection(config['mysql']);

    connection.connect(function(err) {
        if (err) {
            console.error('error connecting: ' + err.stack);
            connection.destroy();
            return;
        }

        connection.query('SELECT * FROM docs WHERE md5="' + md5(doc) + '"', function(err, rows) {
            if (err) {
                console.log('error query: ' + err.stack);
                connection.destroy();
                return;
            }

            sql = ''
            if (rows.length == 0) {
                cache["docs"][doc] = 1
                sql = 'INSERT INTO docs (title, md5, views) VALUES ' +
                    '("' + doc + '", "' + md5(doc) + '", 1)'
            } else {
                cache["docs"][rows[0].title] = rows[0].views + 1
                sql = 'UPDATE docs SET views=views+1 WHERE md5="' + md5(doc) + '"'
            }
            connection.query(sql, function(err, rows) {
                if (err) {
                    console.error('exec failed: ' + sql + ' ' + err.stack);
                } else {
                    console.log('exec success: ' + sql);
                }
                connection.destroy();
            });
        });
    });
}

var DocsModule = {
    'select': select,
}

module.exports = DocsModule;
