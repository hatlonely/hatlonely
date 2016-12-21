var fs = require('fs');
var marked = require('marked');
var express = require('express');
var router = express.Router();

router.get('/', function(req, res, next) {
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

module.exports = router;
