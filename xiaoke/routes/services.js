var fs          = require('fs');
var marked      = require('marked');
var express     = require('express');
var querystring = require('querystring');
var mysql       = require('mysql');
var crypto      = require('crypto');
var config      = require('../config/xiaoke');
var cache       = require('../module/cache')
var docsModule  = require('../module/docs');
var poetry      = require('../module/poetry');

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

            docsModule.select(doc);
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

router.get('/doclist', function(req, res, next) {
    var docsDirectory = '../documents/';
    fs.readdir(docsDirectory, function(err, files) {
        var items = [];
        for (i in files) {
            views = 0;
            if (files[i] in cache['docs']) {
                views = cache['docs'][files[i]];
            }
            item = {
                'doc': files[i],
                'url': '/page?' + querystring.encode({
                    doc: files[i]
                }),
                'views': views
            };
            items.push(item);
        }
        res.send(items);
    });
});

router.get('/poetry', function(req, res, next) {
    res.send(poetry);
});

module.exports = router;
