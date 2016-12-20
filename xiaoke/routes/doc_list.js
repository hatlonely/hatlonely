var fs = require('fs');
var express = require('express');
var router = express.Router();

router.get('/', function(req, res, next) {
    fs.readdir('../documents', function(err, files) {
        res.render('doc_list', {
            'docs': files,
        });
    });
});

module.exports = router;
