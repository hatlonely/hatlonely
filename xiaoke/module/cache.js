var mysql = require('mysql');
var config = require('../config/xiaoke');
var async = require('async');

var cache = {}

async.waterfall([
    function(callback) {
        var connection = mysql.createConnection(config['mysql']);
        connection.connect(function(err) {
            if (err) {
                connection.destroy();
            }
            callback(err, connection);
        });
    },
    function(connection, callback) {
        connection.query('SELECT * FROM docs', function(err, rows) {
            if (err) {
                connection.destroy();
            }
            callback(err, rows);
        });
    }
], function(err, rows) {
    if (err) {
        console.log('error query: ' + err.stack);
        return;
    }

    cache["docs"] = {}
    for (i in rows) {
        cache["docs"][rows[i].title] = rows[i].views
    }
});

module.exports = cache;
