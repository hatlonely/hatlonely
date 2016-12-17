#!/usr/bin/env python3

import httplib2
import pyquery
import threading
import logging
import argparse

http = httplib2.Http(".cache")

class One(object):
    def processOnePage(self, idx):
        oneUrl = "http://wufazhuce.com/one/{0}".format(idx)
        response, content = http.request(oneUrl, "GET")
        if response["status"] != "200":
            logging.warning('{0}\t{1}\t{2}'.format(oneUrl, response["status"], response))
            return None

        jquery = pyquery.PyQuery(content.decode("utf-8"))
        return jquery("div.one-cita").text().strip()

    def processBatchPages(self, **params):
        pageIdxs = params["pageIdxs"]
        for idx in pageIdxs:
            one = self.processOnePage(idx)
            if one:
                print(one)

    def Process(self, idx1=20, idx2=30, threadNum=1):
        pageIdxsList = []
        for i in range(0, threadNum):
            pageIdxsList.append([])
        for idx in range(idx1, idx2):
            pageIdxsList[idx % threadNum].append(idx)

        threads = []
        for i in range(0, threadNum):
            thread = threading.Thread(target=self.processBatchPages, kwargs={"pageIdxs": pageIdxsList[i]})
            thread.start()
            threads.append(thread)

        for i in range(0, threadNum):
            threads[i].join()

def main():
    logging.basicConfig(level=logging.DEBUG,
                        format="%(levelname)s\t%(asctime)s\t[%(filename)s:%(lineno)d]\t%(message)s",
                        datefmt="%Y-%m-%d %H:%M:%S",
                        filename="log/one.log",
                        filemode="a")
    parser = argparse.ArgumentParser()
    parser.add_argument("--idx1", help="起始url", type=int, required=True)
    parser.add_argument("--idx2", help="终止url", type=int)
    parser.add_argument("--threadNum", help="线程数量", type=int, default=1)
    args = parser.parse_args()

    one = One()
    one.Process(args.idx1, args.idx2, args.threadNum)


if __name__ == '__main__':
    main()