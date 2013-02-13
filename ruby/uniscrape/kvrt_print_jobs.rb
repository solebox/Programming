#ssh -L 3307:localhost:3306 kvrt
require 'mysql2'
client = Mysql2::Client.new(:host => '127.0.0.1',
                            :port => port_num,
                            :database => 'db_name',
                            :username => 'username',
                            :password => 'password')

results = client.query('SELECT * FROM CRM_JOBS_job_list')
results.each do |row|
    puts row
end      
