
# !encoding=utf8

# name = raw_input()
# print name
#
t = {"name":"wang", "agent":2}

for (key,value) in t.items():
    print key, value

d = {}
d["key1"] = "value1"

l = "key1" in d
l2 = d.get("key12")
print l
print l2


print [x*x for x in range(1, 11)] #list
print [x*x for x in range(1, 11) if x%2==0] #只取偶数
print [m+n for m in 'abc' for n in 'xyz'] #生成全排列
