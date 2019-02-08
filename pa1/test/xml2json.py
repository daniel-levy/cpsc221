import xml.etree.ElementTree as ET
import json
import os

tests = []

exists = os.path.isfile('resultblock.xml')
if exists: 
    tree = ET.parse('resultblock.xml')
    root = tree.getroot()

    ts = root.find('Group')

    for test in ts.iter('TestCase'):
        tc = {}
        tc['name'] = test.get('name')
        #tc['time'] = test.get('time')
        tc['max_score'] = 1
        tc['visibility'] = 'visible'

        tc['score'] = 1
        result = test.find('Expression')
        if not result==None: 
            resultsuccess = result.get('success')
            if resultsuccess == "false":
                tc['score'] = 0
                tc['output'] = result.find('Expanded').text

        result = test.find('FatalErrorCondition')
        if not result==None: 
            tc['score'] = 0
            tc['output'] = result.text
        
        tests.append(tc)

exists = os.path.isfile('resultchain.xml')
if exists: 
    tree = ET.parse('resultchain.xml')
    root = tree.getroot()

    ts = root.find('Group')
    
    for test in ts.iter('TestCase'):
        tc = {}
        tc['name'] = test.get('name')
        #tc['time'] = test.get('time')
        tc['max_score'] = 1
        tc['visibility'] = 'visible'

        tc['score'] = 1
        result = test.find('Expression')
        if not result==None: 
            resultsuccess = result.get('success')
            if resultsuccess == "false":
                tc['score'] = 0
                tc['output'] = result.find('Expanded').text

        result = test.find('FatalErrorCondition')
        if not result==None: 
            tc['score'] = 0
            tc['output'] = result.text

        tests.append(tc)

results = { 'output': 'pa1--block chain', 'stdout_visibility': 'visible', 'visibility': 'visible'}
results['tests'] = tests

with open('results.json', 'w') as outfile:
    json.dump(results, outfile, sort_keys=True, indent=4, separators=(',', ': '))


