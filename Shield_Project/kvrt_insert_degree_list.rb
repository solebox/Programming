#ssh -L 3307:localhost:3306 kvrt
require 'mysql2'
client = Mysql2::Client.new(:host => '127.0.0.1',
                            :port => 3307,
                            :database => 'kobikvrt_kobi',
                            :username => 'kobikvrt_mainUsr',
                            :password => 'qazwsx321')

results = client.query('SELECT * FROM CRM_JOBS_job_list')
File.readlines("lala.txt").each {|line|
    client.query("INSERT INTO CRM_JOBS_degrees(degree) VALUES('#{line}')")
}
