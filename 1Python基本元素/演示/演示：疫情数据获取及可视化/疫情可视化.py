import requests
import re
import json
from bs4 import BeautifulSoup
from pyecharts import options as opts
from pyecharts.charts import Geo


def getData():
    url = "https://ncov.dxy.cn/ncovh5/view/pneumonia"
    try:
        kv = {'user-agent': 'Mozilla/5.0'}
        r = requests.get(url, headers=kv)
        r.raise_for_status()
        r.encoding = r.apparent_encoding
    except:
        print("获取数据失败")
        exit()
    demo = r.text
    soup = BeautifulSoup(demo, "html.parser")
    area_information = re.search(
        r'\[(.*)\]', str(soup.find('script', attrs={'id': 'getAreaStat'})))
    area_information = json.loads(area_information.group(0))

    cities, nums = [], []
    for area in area_information:
        for city in area['cities']:
            cities.append(city['cityName'])
            nums.append(city['confirmedCount'])
    return list(zip(cities, nums))


data = getData()
data.sort(key=lambda item: item[1])

file = open('疫情数据.txt', 'wt')
for item in data:
    file.write("{}\t{}\n".format(item[0], item[1]))
file.close()

geo = Geo(opts.InitOpts(width="950px", height="650px",
                        page_title="全国疫情分析")).add_schema(maptype="china")
for index in range(len(data)):
    item = data[index]
    try:
        geo.add("全部数据", [item], is_selected=True)

        if item[1] == 0:
            geo.add("0", [item], is_selected=False)
        elif item[1] <= 100:
            geo.add("(0, 100]", [item], is_selected=False)
        elif item[1] <= 500:
            geo.add("(100, 500]", [item], is_selected=False)
        elif item[1] <= 1000:
            geo.add("(500, 1000]", [item], is_selected=False)
        else:
            geo.add("> 1000", [item], is_selected=False)

        if index >= len(data) - 20:
            geo.add("前20", [item], is_selected=False)
    except:
        pass
geo.set_series_opts(label_opts=opts.LabelOpts(is_show=False))
geo.set_global_opts(visualmap_opts=opts.VisualMapOpts(),
                    title_opts=opts.TitleOpts(title="疫情数据"),
                    )
geo.render(path='疫情地图.html')
