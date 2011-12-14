#!/usr/bin/env python
import urllib
from BeautifulSoup import BeautifulSoup
url = "http://www.bis.org.il/search_res_bank.asp?PageId=1"
page = urllib.urlopen(url)
html = page.read()
page.close()
soup = BeautifulSoup(html)
a = soup.fetch("table",{'class':'tab_b'})
b =[]
for i in a:
    b.append(i['onclick'])
    for j in i.fetch("font",{'class':'w3'}):
        b.append(j)
    b.append("\n")
file = open('try_it.txt','w')
for i in b:
    file.write(str(i))
    file.write("\n")
file.close()
