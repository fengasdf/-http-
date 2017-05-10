# -*- coding: utf-8 -*-
import urllib2

class my_download(object):
    def download(self, url):
        if url is None:
            return None
        try:
            reponse = urllib2.urlopen(url)
            if reponse.getcode() != 200:
                return None
            else:
                return reponse.read()
        except(urllib2.HTTPError):
            return None
        except(urllib2.URLError):
            return None

