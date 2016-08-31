# yaarf

## Introduction

Yet Another Alert Reporting Framework

A drop in replacement for snarf (http://tools.netsa.cert.org/snarf/) which instead HTTP POSTs
alerts in JSON to webservice.

To get analysis-pipeline to use the library instead of the original snarf either modify the analysis-pipeline
build scripts or simply "cp /usr/lib64/pkgconfig/libyaarf.pc /usr/lib64/pkgconfig/libsnarf.pc".

Then set SNARF_DESTINATION in pipeline.conf to the URL of your webservice.

eg SNARF_DESTINATION=http://localhost/alert

## Notes

Library is not complete.  Only the required functionality for analysis-pipeline is implemented.

