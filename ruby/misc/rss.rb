require 'rss/maker'
version = "2.0"
destination = "test_maker.xml"

content = RSS::Maker.make(version) do |m|
    m.channel.title = "Example - Accademic Stock"
    m.channel.link = "http://www.example.com/"
    m.channel.description = "Accademic stock"
    m.channel.updated = Time.now
    m.items.do_sort = true #sort items by date

    i = m.items.new_item
    i.title = "kovets ledugma"
    i.link = "http://dugma.com"
    i.date = Time.now

    image = RSS::Rss::Channel::Image.new
    image.url = "http://th810.photobucket.com/albums/zz26/hwangtaeny/cp%20yulti/th_siny.jpg"
end
File.open(destination,"w") do |f|
f.write(content)
end
