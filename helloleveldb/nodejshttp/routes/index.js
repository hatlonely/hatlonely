var express = require('express');
var levelup = require('level');
var router = express.Router();

var db = levelup('./data');

router.get('/set', function(req, res, next) {
    var key = req.query.key;
    var value = req.query.value;
    if (key && value) {
        db.put(key, value, function (err) {
            if (err) {
                res.send({'errorCode': -1, 'message': err});
            } else {
                res.send({'errorCode': 0, 'message': 'ok', 'key': key, 'value': value});
            }
        });
    } else {
        res.send({'errorCode': 1, 'message': 'miss [key] or [value] parameter'});
    }
});

router.get('/get', function(req, res, next) {
    var key = req.query.key;
    if (key) {
        db.get(key, function (err, value) {
            if (err) {
                res.send({'errorCode': -1, 'message': String(err)});
            } else {
                res.send({'errorCode': 0, 'message': 'ok', 'key': key, 'value': value});
            }
        })
    } else {
        res.send({'errorCode': 1, 'message': 'miss [key] parameter'});
    }
});

module.exports = router;
