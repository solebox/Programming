#!/usr/bin/ruby -w

class CsvToHtml
	def initialize
	@top_markup = '		
	<!DOCTYPE HTML>
	<html>
	<head>
	<title>...</title>
	<meta http-equiv=Content-Type content="text/html; charset=UTF-8">
	<style type="text/css">
	.body{ direction: rtl; }
	.book{ page-break-after: always; }
	.bookshelf{ text-align: left; font-size: 30px; }
	.bookname{ text-align: center; font-size: 30px; font-weight: bold; }
	.bookdesc{ text-align: center; font-size: 30px; margin-top: 18px; }
	.bookauthor{ text-align: center; font-size: 30px; margin-top: 18px; }
	</style>
	</head>
	<body>
	    <div class="body">'
	@bottom_markup = '</div>
			</body>
			</html>'
	end
	def read_csv(csv_filename)
		csv = File.read(csv_filename).split("\n")
		return csv
	end
	def write_html(html_filename,csv_filename)
		csv = read_csv(csv_filename)
		
		html_file = File.new(html_filename,"a")
		html_file.puts @top_markup
		csv.each do |line|
			inject_div(html_file,line)	
		end
		html_file.puts @bottom_markup
	end
	def inject_div(html_file,line)
		words = line.split(",")
		html_file.puts %Q~<div class="book">\n
				\t<div class="bookshelf">#{words.shift}</div>\n
				\t<div class="bookname">#{words.shift}</div>\n
				\t<div class="bookdesc">#{words.shift}</div>\n
				\t<div class="bookauthor">#{words.shift}</div>\n
				</div>~
	end
end
