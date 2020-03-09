const webpack = require('webpack');
const path = require('path');
const CopyWebpackPlugin = require('copy-webpack-plugin');

const developmentEnvironment = process.env.NODE_ENV === 'development';
const productionEnvironment = process.env.NODE_ENV === 'production';

module.exports = {
  entry: './src/js/Index.bs.js',
  devtool: 'source-map',
  devServer: {
    contentBase: path.join(__dirname, 'src'),
    port: 3000,
    open: true,
    overlay: true,
    hot: true,
    stats: {
      assets: false,
      builtAt: true,
      cached: false,
      cachedAssets: false,
      children: false,
      chunks: false,
      colors: true,
      depth: false,
      entrypoints: false,
      env: true,
      errors: true,
      errorDetails: true,
      errorStack: true,
      hash: true,
      logging: false,
      outputPath: false,
      performance: true,
      reasons: false,
      source: false,
      timings: false,
      usedExports: false,
      version: true,
      warnings: true,
      chunkRelations: false,
    },
    index: 'index.html',
    historyApiFallback: true,
  },
  mode: productionEnvironment ? 'production' : 'development',
  entry: ['./src/js/Index.bs.js'],
  output: {
    path: `${__dirname}/dist`,
    publicPath: '/',
    filename: 'bundle.js',
    chunkFilename: './chunks/[name].js',
  },
  stats: {
    colors: true,
    errorDetails: true,
  },
  plugins: [
    new webpack.DefinePlugin({
      'process.env.NODE_ENV': JSON.stringify(process.env.NODE_ENV),
    }),
    new CopyWebpackPlugin([
      { from: 'src/images', to: 'images' },
      { from: 'src/assets', to: 'assets' },
      { from: 'src/index.html' },
    ]),
  ],
  module: {
    rules: [
      {
        test: /\.bs\.js$/,
        exclude: /(node_modules|bower_components)/,
        use: [
          {
            loader: 'babel-loader',
            options: {
              presets: [
                [
                  '@babel/preset-env',
                  {
                    modules: false,
                    targets: {
                      browsers: ['> 1%', 'last 2 versions', 'Firefox ESR', 'Opera 12.1', 'Safari 7', 'ie 9'],
                    },
                  },
                ],
              ],
            },
          },
        ],
      },
    ],
  },
  target: 'web',
};
