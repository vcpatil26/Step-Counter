#!/bin/bash
virtualenv virt
source virt/bin/activate
pip install pyserial
deactivate
