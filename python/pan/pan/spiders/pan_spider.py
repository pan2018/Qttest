import scrapy

class WishSpider(scrapy.Spider):
    name = "wish"
    allowed_domains = ["shpostwish.com"]
    start_urls = [
        "http://www.shpostwish.com/tracking",
    ]

    def parse(self, response):
        filename = response.url.split("/")[-2]
        with open(filename, 'wb') as f:
            f.write(response.body)