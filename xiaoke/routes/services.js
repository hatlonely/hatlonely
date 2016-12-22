var fs = require('fs');
var marked = require('marked');
var express = require('express');
var router = express.Router();

router.get('/mdsource', function(req, res, next) {
    doc = req.query.doc;
    fs.readFile('../documents/' + doc, 'utf-8', (err, data) => {
        if (err) {
             res.send(JSON.stringify({
                'markdown': err
            }));
        } else {
            res.send(JSON.stringify({
                'markdown': data
            }));
        }
    });
});

router.get('/code', function(req, res, next) {
    doc = req.query.doc;
    fs.readFile('../' + doc, 'utf-8', (err, data) => {
        if (err) {
            res.send(err);
        } else {
            res.send(data);
        }
    });
});

module.exports = router;
