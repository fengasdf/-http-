# -*- coding: utf-8 -*-
import analze
import output
import url
import download
import sys
reload(sys)
sys.setdefaultencoding( "utf-8" )
class Solution(object):
    def __init__(self):
        self._url = url.my_url()
        self._download = download.my_download()
        self._analze = analze.my_analze()
        self._output = output.my_output()
        self._url.add('http://www.sohu.com/')

    def craw(self, aim):
        count = 0
        while count <= 10:
            
            str = self._url.new()
            print str
            if str is None:
                break
            res = self._download.download(str)
            if res is None:
                continue
            new_strs, data = self._analze.analze(str, res, count, aim)
            if new_strs is None and data is None:
                continue
            self._url.adds(new_strs)
            self._output.collect_data(data)
            count = count + 1
        self._output.output()






    

