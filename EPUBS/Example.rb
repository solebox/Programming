#-*- coding: utf-8 -*-
#require 'rubygem'
require 'gepub'
#old_book_path = ARGV[0]
#old_book = GEPUB::Book.parse(File.open(old_book_path))
#old_book_version = old_book.version

book = GEPUB::Book.new
book.set_main_id('http:/example.jp/bookid_in_url', 'BookID', 'URL')
book.language = 'he'

# you can add metadata and its property using block
book.add_title('כותרת הספר', nil, GEPUB::TITLE_TYPE::MAIN) {
  |title|
  title.lang = 'he'
  title.file_as = 'GEPUB Sample Book'
  title.display_seq = 1
  title.add_alternates(
                       'en' => 'GEPUB Sample Book (Japanese)',
                       'el' => 'GEPUB δείγμα (Ιαπωνικά)',
                       'th' => 'GEPUB ตัวอย่าง (ญี่ปุ่น)')
}
book.add_creator('יוצר הספר') {
  |creator|
  creator.display_seq = 1
  creator.add_alternates('en' => 'book creator')
}
book.add_contributor('קונטריביוטר').set_display_seq(1).add_alternates('en' => 'creator')
book.add_contributor('アサガヤデンショ').set_display_seq(2).add_alternates('en' => 'Asagaya Densho')
book.add_contributor('湘南電書鼎談').set_display_seq(3).add_alternates('en' => 'Shonan Densho Teidan')
book.add_contributor('電子雑誌トルタル').set_display_seq(4).add_alternates('en' => 'eMagazine Torutaru')

imgfile = File.join(File.dirname(__FILE__), 'genocide_book_001/OEBPS/images/', 'cover.jpg')
File.open(imgfile) do
  |io|
  book.add_item('genocide_book_001/OEBPS/images/cover.jpg',io).cover_image
end

# within ordered block, add_item will be added to spine.
book.ordered {
  book.add_item('text/chap1.xhtml').add_content(StringIO.new('<html xmlns="http://www.w3.org/1999/xhtml"><head><title>c1</title></head><body><p>the first page</p></body></html>')).toc_text('Chapter 1')
  book.add_item('text/chap1-1.xhtml').add_content(StringIO.new('<html xmlns="http://www.w3.org/1999/xhtml"><head><title>c2</title></head><body><p>the second page</p></body></html>')) # do not appear on table of contents
  book.add_item('text/chap2.xhtml').add_content(StringIO.new('<html xmlns="http://www.w3.org/1999/xhtml"><head><title>c3</title></head><body><p>the third page</p></body></html>')).toc_text('Chapter 2')
  # to add nav file:
  # book.add_item('path/to/nav').add_content(nav_html_content).add_property('nav')
}
epubname = File.join(File.dirname(__FILE__), 'example_test.epub')

# if you do not specify your own nav document with add_item,
# simple navigation text will be generated in generate_epub.
# auto-generated nav file will not appear on spine.
book.generate_epub(epubname)
