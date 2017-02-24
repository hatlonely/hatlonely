var config = {
    'mysql': {
        host: 'localhost',
        user: 'hatlonely',
        password: process.env['HLDBPASSWD'] || '12345678',
        database: 'hatlonely'
    }
}

module.exports = config;
