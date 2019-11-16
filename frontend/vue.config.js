module.exports = {
  transpileDependencies: ['vuetify'],
  devServer: {
    host: 'localhost',
    port: 8080,
    headers: {
      'Access-Control-Allow-Origin': '*',
      'Access-Control-Allow-Methods': 'GET, POST, PUT, DELETE, PATCH, OPTIONS',
      'Access-Control-Allow-Headers':
        'X-Requested-With, content-type, Authorization',
    },
    proxy: {
      '**': {
        target: {
          host: 'localhost',
          protocol: 'http:',
          port: 34568,
        },
        secure: false,
        changeOrigin: true,
        onProxyRes(proxyRes) {
          if (proxyRes.headers.location) {
            // eslint-disable-next-line prefer-destructuring
            let location = proxyRes.headers.location;
            console.log(`LOCATION: ${proxyRes.headers.location}`);
            location = location.replace('localhost:34568', 'localhost:8080');
            // eslint-disable-next-line no-param-reassign
            proxyRes.headers.location = location;
            console.log(`REPLACED: ${proxyRes.headers.location}`);
          }
        },
      },
    },
  },
};
