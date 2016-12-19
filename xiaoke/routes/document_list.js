var fs = require('fs');
var express = require('express');
var router = express.Router();

router.get('/', function(req, res, next) {
    fs.readdir('../documents', function (err, files) {
        res.send(JSON.stringify(files));
    });
});

module.exports = router;
