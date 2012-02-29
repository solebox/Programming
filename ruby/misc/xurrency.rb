wsdl_url = 'http://xurrency.com/api.wsdl'
proxy = SOAP::WSDLDriverFactory.new(wsdl_url).create_rpc_driver
rate = proxy .getValue('1','usd','eur')
puts "Rate: #{rate}"
