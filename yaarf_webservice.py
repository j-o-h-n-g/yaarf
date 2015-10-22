#!/usr/bin/python
import sys
import argparse
import cherrypy
import json
import datetime
import logging

class _JSONEncoder(json.JSONEncoder):
    def default(self, obj):
        if isinstance(obj, datetime.date):
            return obj.isoformat()
        return super(_JSONEncoder,self).default(obj)

    def iterencode(self, value):
        # Adapted from cherrypy/_cpcompat.py
        for chunk in super(_JSONEncoder,self).iterencode(value):
            yield chunk.encode("utf-8")

json_encoder = _JSONEncoder()

def json_handler(*args, **kwargs):
	# Adapted from cherrypy/lib/jsontools.py
	value = cherrypy.serving.request._json_inner_handler(*args, **kwargs)
	return json_encoder.iterencode(value)


class Alert(object):

	exposed = True
	@cherrypy.tools.json_out(handler=json_handler)
        @cherrypy.tools.json_in()
	def POST(self,*id,**kwargs):
		data=cherrypy.request.json

		print data
		if "type:Evaluation" in data['envelope']['analysis_tags']:
			# Do something
			pass
		else:
			# Do something else
			pass


class Root(object):
	pass

class LoggerWriter:
    def __init__(self, logger, level):
        self.logger = logger
        self.level = level

    def write(self, message):
        if message != '\n':
            self.logger.log(self.level, message)


if __name__ == "__main__":
	parser=argparse.ArgumentParser()
	parser.add_argument("--logfile",action="store",dest="logfile",help="Path to logfile",default=False)
	args=parser.parse_args()
	if not args.logfile:
		parser.error("Unrecognised command line arguments")
	
	logging.basicConfig(level=logging.DEBUG,
                    format='%(asctime)s %(name)-12s %(levelname)-8s %(message)s',
                    datefmt='%m-%d %H:%M',
                    filename=args.logfile,
                    filemode='a')
	logging.info("yaarf webservice started")

	logger = logging.getLogger("yaarfweb")
	#sys.stdout = LoggerWriter(logger,logging.INFO)
	#sys.stderr = LoggerWriter(logger,logging.ERROR)

	root=Root()
	root.alert=Alert()

	conf = { 'global': {'server.socket_host': '0.0.0.0',
			'server.socket_port':8080,
		},
	 	'/': {'request.dispatch': cherrypy.dispatch.MethodDispatcher(),}}

	cherrypy.quickstart(root,"/",conf)

