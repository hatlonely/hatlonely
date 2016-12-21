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
                'query': querystring.encode({doc: files[i]})
            };
            items.push(item);
        }
        res.render('doc_list', {
            'items': items
        });
    });
});

module.exports = router;
