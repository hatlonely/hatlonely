var fs = require('fs');
var marked = require('marked');
var express = require('express');
var router = express.Router();

marked.setOptions({
  renderer: new marked.Renderer(),
  gfm: true,
  tables: true,
  breaks: true,
  pedantic: true,
  sanitize: true,
  smartLists: true,
  smartypants: true
});

router.get('/', function(req, res, next) {
    fs.readFile('../documents/' + req.query.d, 'utf-8', (err, data) => {
        if (err) {
            res.render('error', { 'error': err });
        } else {
            res.send(marked(data))
        }
    });
});

module.exports = router;
