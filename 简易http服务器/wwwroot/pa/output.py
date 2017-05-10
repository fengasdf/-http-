# -*- coding: utf-8 -*-
class my_output(object):
    def __init__(self):
       self.datas = []

    def collect_data(self, data):
        if data is not None:
            self.datas.append(data)

    def output(self):
        fout = open('output.html', 'w')


        for data in self.datas:
            if data['title'] is None or data['title'] is '':
                continue
            fout.write("<meta charset=\'utf-8\'>")
            fout.write("<div id=\"header\">")
            str = (data['title'].__getattribute__('text'))
            fout.write("<h1>%s</h1>" % str)
            fout.write("</div>")
            fout.write("<h3>%s</h3><a href=\"%s\">网页快照</a>" % (data['url'], data['url']))
            fout.write("%c" % '\n')
