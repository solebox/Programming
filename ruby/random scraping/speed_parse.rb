#!/usr/bin/env ruby1.9.1
# encoding: UTF-8


require 'rexml/document'
require 'net/http'


uri = URI("http://www.bis.org.il/search_res_bank.asp?PageId=1")
page = Net::HTTP.get(uri)
xmldoc = REXML::Document.new(page)

