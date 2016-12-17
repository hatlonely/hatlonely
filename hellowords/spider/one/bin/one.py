#!/usr/bin/env python3

import httplib2
import pyquery
import threading
import logging
import logging.config
import argparse
import configparser
import os

http = httplib2.Http(".cache")


class Logger(object):
    infoLogger = logging.getLogger("info")
    warnLogger = logging.getLogger("warn")


class OneWord(object):
    def ProcessOnePage(self, idx):
        oneUrl = "http://wufazhuce.com/one/{0}".format(idx)
        response, content = http.request(oneUrl, "GET")
        if response["status"] != "200":
            Logger.warnLogger.warning('{0}\t{1}\t{2}'.format(oneUrl, response["status"], response))
            return None

        jquery = pyquery.PyQuery(content.decode("utf-8"))
        return "{0}\t{1}".format(oneUrl, jquery("div.one-cita").text().strip())

    def ProcessBatchPages(self, idx1, idx2):
        for idx in range(idx1, idx2):
            one = self.ProcessOnePage(idx)
            if one:
                Logger.infoLogger.critical(one)

class OneAuto(object):
    def __init__(self, fname):
        self.progressFname = "conf/one.progress"
        self.threadNum = 1
        config = configparser.ConfigParser()
        config.read(fname)
        if config.has_option("one", "progress"):
            self.progressFname = config["one"]["progress"]
        if config.has_option("one", "threadNum"):
            self.threadNum = int(config["one"]["threadNum"])
        self.progress = self.readProgress() + 1

    def readProgress(self):
        if not os.path.exists(self.progressFname):
            return 0
        with open(self.progressFname) as fd:
            return int(fd.read())

    def saveProgress(self, progress):
        with open(self.progressFname, 'w') as fd:
            fd.write('{0}'.format(progress))

    def AutoRun(self, num=3):
        oneWord = OneWord()
        for idx in range(self.progress, self.progress + num):
            one = oneWord.ProcessOnePage(idx)
            if one:
                Logger.infoLogger.info(one)
                self.progress = idx
                self.saveProgress(self.progress)


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("--idx1", help="起始url", type=int, default=0)
    parser.add_argument("--idx2", help="终止url", type=int, default=0)
    parser.add_argument("--num", help="获取条数", type=int, default=3)
    args = parser.parse_args()

    if args.idx1 == 0 and args.idx2 == 0:
        logging.config.fileConfig("conf/logging.conf")
        oneAuto = OneAuto("conf/one.conf")
        oneAuto.AutoRun(args.num)
    else:
        logging.root.setLevel(logging.INFO)
        oneWord = OneWord()
        oneWord.ProcessBatchPages(args.idx1, args.idx2)


if __name__ == '__main__':
    main()