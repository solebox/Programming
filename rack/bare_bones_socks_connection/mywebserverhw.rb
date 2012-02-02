#!/usr/bin/env ruby1.9.1
require 'socket'
webserver = TCPServer.new('127.0.0.1',7000)
while (session = webserver.accept)
    session.print "HTTP/1.1 200/OK\r\nContent-type:text/html\r\n\r\n"
    s = "I'm Listening... tell me a bit about yourself.."
    while s.to_s.chomp != ""
        session.print s+"<BR>"
        s = session.gets
    end
    session.close
end
