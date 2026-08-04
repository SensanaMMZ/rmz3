import subprocess,re,os,sys
q=subprocess.run([sys.executable, os.path.join(os.environ['S'],'queue.py')],capture_output=True,text=True).stdout
rows=[]
for l in q.split('\n'):
    m=re.match(r'\s*(\d+)\s+(\S+)\s+(\S+)',l)
    if m and m.group(3).endswith('.inc'):
        rows.append((int(m.group(1)),m.group(2),m.group(3).replace(chr(92),'/')))
hi=0; okrows=[]
pat=re.compile(r'\b(?:mov\s+(?:r\d+,\s*(?:sl|sb|r8|ip)|(?:sl|sb|r8|ip),)|add\s+(?:r8|sb|sl|ip)\b)')
for size,sym,inc in rows:
    try: txt=open(inc,encoding='utf-8',errors='ignore').read()
    except Exception: continue
    i=txt.find(sym+':')
    if i<0: continue
    j=txt.find('thumb_func_start', i)
    body=txt[i:j if j>0 else len(txt)]
    if pat.search(body): hi+=1
    else: okrows.append((size,sym,inc))
print("queue rows parsed:", len(rows))
print("uses r8/sb/sl/ip (non-viable class):", hi)
print("clean of high registers:", len(okrows))
print()
for r in sorted(okrows)[:20]: print("  %5d %-32s %s"%r)
