var mysql = require('mysql');
var config = require('../config/xiaoke');

var cache = {}

function init() {
    var connection = mysql.createConnection(config['mysql']);
    connection.connect(function(err) {
        if (err) {
            console.error('error connecting: ' + err.stack);
            connection.destroy();
            return;
        }

        connection.query('SELECT * FROM docs', function(err, rows) {
            if (err) {
                console.log('error query: ' + err.stack);
                connection.destroy();
                return;
            }

            cache["docs"] = {}
            for (i in rows) {
                cache["docs"][rows[i].title] = rows[i].views
            }
        });
    })
}

init();

module.exports = cache;
