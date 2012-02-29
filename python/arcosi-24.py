#!/usr/bin/env python
# Scrapes OSINT data for import into ESM via CEF/Syslog
# gregcmartin at gmail.com
# http://infosec20.blogspot.com
#
# ArcOSI v2.4
#----------------------------------------------------------------------------
# The MIT License
#
#Copyright 2011 Greg C. Martin
#
#Permission is hereby granted, free of charge, to any person obtaining a copy
#of this software and associated documentation files (the "Software"), to deal
#in the Software without restriction, including without limitation the rights
#to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
#copies of the Software, and to permit persons to whom the Software is
#furnished to do so, subject to the following conditions:
#
#The above copyright notice and this permission notice shall be included in
#all copies or substantial portions of the Software.
#
#THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
#IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
#FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
#AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
#LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
#OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
#THE SOFTWARE.
#
import urllib2
import re
import socket
import sys
import time

if (len(sys.argv) > 1):
    dest = sys.argv[1]
else:
    print 'Usage: arcosi.py <connecter ip> \n'
    print 'ex. ./arcosi.py 127.0.0.1 \n'
    sys.exit()


PROXY = {
'enabled' : 'no', # Change this to yes if using ArcOSI with a proxy
'user' : 'none',
'pass' : 'none',
'host' : "proxy.name.com",
'port' : 3128 # or 8080 or whatever
}

FACILITY = {
        'kern': 0, 'user': 1, 'mail': 2, 'daemon': 3,
        'auth': 4, 'syslog': 5, 'lpr': 6, 'news': 7,
        'uucp': 8, 'cron': 9, 'authpriv': 10, 'ftp': 11,
        'local0': 16, 'local1': 17, 'local2': 18, 'local3': 19,
        'local4': 20, 'local5': 21, 'local6': 22, 'local7': 23,
}

LEVEL = {
        'emerg': 0, 'alert':1, 'crit': 2, 'err': 3,
        'warning': 4, 'notice': 5, 'info': 6, 'debug': 7
}

IPSOURCE = [
		'http://www.mtc.sri.com/live_data/attackers/', 
		'http://isc.sans.edu/reports.html',
		'https://zeustracker.abuse.ch/blocklist.php?download=ipblocklist',
		'https://spyeyetracker.abuse.ch/blocklist.php?download=ipblocklist', 
		'http://www.projecthoneypot.org/list_of_ips.php',
]

DOMSOURCE = [ 
		'https://secure.mayhemiclabs.com/malhosts/malhosts.txt', 
		'https://zeustracker.abuse.ch/blocklist.php?download=domainblocklist',
		'https://spyeyetracker.abuse.ch/blocklist.php?download=domainblocklist',
		'http://mirror1.malwaredomains.com/files/BOOT',
		'http://www.malwaredomainlist.com/hostslist/hosts.txt',
		'http://www.malware.com.br/cgi/submit?action=list',
]


# Set Global Timeout
socket.setdefaulttimeout(30)

#Set Regex
ip_regex = re.compile(r"\b(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\.(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\.(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\.(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\b")
dom_regex = re.compile(r'([\w\d.]+\.)+(com|org|edu|cn|ru|biz|cc|kr|cz|jo|cx|info|in|ua|br|ag|pt|pl|au|dk|hu|nl|md|su|tv)')


# Simple HTTP(S) Scraper
def scrape(url, regex):
		try:
			content = urllib2.urlopen(url).read()
			print '\nGrabbing list from: '+url+'\n'
			time.sleep(1)
			results = re.findall(regex, content)
			return results
		except:
			print 'Failed connection to: '+url+' skipping...'
			print '\n'
			time.sleep(1)
			return 'failed'


def syslog(message, level=LEVEL['notice'], facility=FACILITY['daemon'], host='localhost', port=514):
        sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        data = '<%d>%s' % (level + facility*8, message)
        sock.sendto(data, (host, port))
        sock.close()


def getosint():
    for source in DOMSOURCE:
        op = scrape(source, dom_regex)
        if op != 'failed':
            for i in op:
                domain = i[0]+i[1]
                print 'Sending event for %s from %s' % (domain, source)
                cef = 'CEF:0|ArcOSI|ArcOSI|1.0|100|Known Malicious '+'Domain'+'|1|shost='+domain+' msg='+source
                time.sleep(.01)
                syslog(cef, host=dest)
    for source in IPSOURCE:
        op = scrape(source, ip_regex)
        if op != 'failed':
            for i in op:
                ip = i[0]+'.'+i[1]+'.'+i[2]+'.'+i[3]
                print 'Sending event for %s from %s' % (ip, source)
                cef = 'CEF:0|ArcOSI|ArcOSI|1.0|100|Known Malicious '+'Host'+'|1|src='+ip+' msg='+source
                time.sleep(.01)
                syslog(cef, host=dest)

#Main

#Check/Initialize Proxy Config
if PROXY['enabled'] == 'yes':
	proxy_support = urllib2.ProxyHandler({"http" : \
	"http://%(user)s:%(pass)s@%(host)s:%(port)d" % PROXY})
	opener = urllib2.build_opener(proxy_support, urllib2.HTTPHandler)
	urllib2.install_opener(opener)

# Go scraper
getosint()
