# -*- coding: utf-8 -*-
def testpan(url):
	url_m=url[:-1]  #截取字符串，从头到倒数第2个
	url_t = '%s%s%s'%("https://www.17track.net/zh-cn/track?nums=",url_m,"&fc=0")
#	driver.get(url)
	print url_t
	
url_list=["LM413299111CN",
			"LW421699133CN",
			"LW416896215CN",
			"LB706860483GB",
			"RS889881380NL",
			"RS660999444GB",
			"RS664668425CN",
			"LW409940465CN",
			"LM437222647CN",
			"RS658455130CN",
			"LM433670185CN",
			"RS660895475GB",
			"OZ021330625PY",
			"RS660895475GB",
			"RS660895475GB"
]
'''
with open('shipp.txt','a+') as f:
	 for i in url_list:
		f.write(i)
		f.write('\n')
'''
with open('shipp.txt','r') as f:
	pan = f.readlines();
for i in pan:
	testpan(i)
	
f.close()
