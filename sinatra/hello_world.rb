#!/usr/bin/env ruby1.9.1
#hello world
require 'sinatra'
get '/' do
    'hello world'
end
get '/:p' do
    if params[:p] == 'vins' 
    '<html>
    <head></head>
    <body>
        <h1>whats up!</h1>
    </body>
    </html>'
    else
    '<html>
    <head></head>
    <body>
        <h1>'"Hello #{params[:p]}"'</h1>
    </body>
    </html>'
    
    end
end
