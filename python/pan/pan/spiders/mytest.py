# -*- coding: utf-8 -*-
import scrapy
from pan.items import PanItem

class MytestSpider(scrapy.Spider):
    name = 'mytest'
    allowed_domains = ['17track.net']
    start_urls = ['https://www.17track.net/zh-cn/track?nums=LM413299111CN&fc=0']

    def parse(self, response):
		self.log('A response from %s just arrived' % response.url)
		sel = scrapy.Selector(response)
		#for h3 in response.xpath('//span[@class="divt"]').extract():
		for h3 in response.xpath("//span[@class='newest']").extract():
			yield PanItem(title=h3)
			
		#for url in response.xpath('//a/@href').extract():
		#	yield scrapy.Request(url,callback=self.parse)
        #pass

		
#scrapy genspider mytest shpostwish.com