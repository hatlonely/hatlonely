var fs = require('fs');
var marked = require('marked');
var express = require('express');
var querystring = require('querystring');
var router = express.Router();


router.get('/', function(req, res, next) {
    doc = req.query.doc;
    res.render('page', {
        'title': doc,
        'url': '/services/mdsource?' + querystring.encode({doc: req.query.doc})
    })
});

module.exports = router;
