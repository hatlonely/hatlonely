var fs = require('fs');
var marked = require('marked');
var express = require('express');
var querystring = require('querystring');
var router = express.Router();

router.get('/mdsource', function (req, res, next) {
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

router.get('/code', function (req, res, next) {
    doc = req.query.doc;
    fs.readFile('../' + doc, 'utf-8', (err, data) => {
        if (err) {
            res.send(err);
        } else {
            res.send(data);
        }
    });
});

router.get('/doclist', function (req, res, next) {
    var docsDirectory = '../documents/';
    fs.readdir(docsDirectory, function(err, files) {
        var items = [];
        for (i in files) {
            item = {
                'doc': files[i],
                'url': '/page?' + querystring.encode({doc: files[i]})
            };
            items.push(item);
        }
        res.send(items);
    });
})

module.exports = router;
