#!/usr/bin/ruby
require 'savon'
client = Savon::Client.new "http://www.webservicex.net/CurrencyConvertor.asmx?WSDL"
#want to know available actions? client.wsdl.soap_actions
result = client.conversion_rate do |soap| 
	soap.body = {"wsdl:FromCurrency" => "USD", "wsdl:ToCurrency" => "AUD"}
end
print result.to_hash
