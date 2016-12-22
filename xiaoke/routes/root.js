var fs = require('fs');
var express = require('express');
var querystring = require('querystring');
var router = express.Router();

var docsDirectory = '../documents/';

router.get('/', function(req, res, next) {
    fs.readdir(docsDirectory, function(err, files) {
        var items = [];
        for (i in files) {
            item = {
                'doc': files[i],
                'url': '/page?' + querystring.encode({doc: files[i]})
            };
            items.push(item);
        }
        res.render('doc_list', {
            'items': items
        });
    });
});

router.get('/page', function(req, res, next) {
    doc = req.query.doc;
    res.render('page', {
        'title': doc,
        'url': '/services/mdsource?' + querystring.encode({doc: req.query.doc})
    })
});

router.get('/code', function(req, res, next) {
    doc = req.query.doc;
    res.render('code', {
        'title': doc,
        'url': '/services/code?' + querystring.encode({doc: req.query.doc})
    })
});

module.exports = router;
