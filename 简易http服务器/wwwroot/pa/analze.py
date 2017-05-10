# -*- coding: utf-8 -*-
import bs4
from bs4 import BeautifulSoup
from itertools import chain
import re
import urlparse

class my_analze(object):
    def __search__(self, soup , aim , Links, start):
        urls = []
        finder = u'电影'
        for link in Links:
            text = link.__getattribute__('text')
            if finder not in text:
                continue
            str = link.__str__()
            i = 0
            str2 = None
            try:
                i = str.index(aim)
                str2 = str[i+6:]
            except(ValueError):
                continue
            pos = 0
            for ch in str2:
                if ch != '"':
                    pos = pos + 1
                else:
                    break
            url = str2[:pos]
            if 'http' not in url and '//' in url:
                url = 'http:' + url
            if '//' not in url:
                url = start + url
            urls.append(url)
        return urls


    def __find_data_and_urls(self, soup, url, flag, aim):
        urls = []
        data = {}
        data['url'] = url
        title = soup.find(re.compile("h[1-6]"))
        if title is None:
            title = soup.find('span')
        if title.__str__() is None:
            return None, None
        data['title'] = title
        if flag == 0:
            Links = soup.find_all('li')
        else:
            Links = soup.find_all('div')
        ret1 = self.__search__(soup, 'href="', Links, url)
        urls = ret1
        return urls, data

   
      

    def analze(self, url, strs, flag, aim):
        soup = BeautifulSoup(strs, 'html.parser', from_encoding = 'utf-8')
        
        urls, data = self.__find_data_and_urls(soup, url, flag, aim)
        return urls, data