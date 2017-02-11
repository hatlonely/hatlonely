var fs          = require('fs');
var express     = require('express');
var querystring = require('querystring');
var router      = express.Router();

router.get('/', function(req, res, next) {
    res.render('doclist', {
        'url': '/services/doclist'
    });
});

router.get('/page', function(req, res, next) {
    doc = req.query.doc;
    res.render('page', {
        'title': doc,
        'url': '/services/mdsource?' + querystring.encode({
            doc: req.query.doc
        })
    });
});

router.get('/code', function(req, res, next) {
    doc = req.query.doc;
    res.render('code', {
        'title': doc,
        'url': '/services/code?' + querystring.encode({
            doc: req.query.doc
        })
    });
});

router.get('/poetry', function(req, res, next) {
    res.render('poetry', {
        'title': '诗歌',
        'url': '/services/poetry'
    });
})

module.exports = router;
