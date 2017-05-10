# -*- coding: utf-8 -*-
class my_url():
    def __init__(self):
        self.old_dict = set()
        self.new_dict = set()
    def add(self, str):
        if (str not in self.new_dict) and (str not in self.old_dict):
            self.new_dict.add(str)

    def empty(self):
        if len(self.new_dict) == 0:
            return 0
        else:
            return 1

    def new(self):
        try:
            item = self.new_dict.pop()
            self.old_dict.add(str)
            return item
        except(KeyError):
            return None

    def adds(self, arr):
        for url in arr:
            self.add(url)

