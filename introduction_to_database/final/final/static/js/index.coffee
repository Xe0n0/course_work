pageid = 1

pageClick = (e, oldPage, newPage) ->
    pageid = newPage
    $.post "/eatings/top.json", { "pageid": newPage }, load_did_success, "json"


load_did_success = (json, textStatus, jqXHR) ->
    pagecount = json.pagecount
    if (json.pagecount)
        $("div#heading").html "最近热门餐厅 <strong>" + pageid.toString() + "/" + pagecount + "</strong>"
        $("div#content").html json.content
        $("#pager").bootstrapPaginator { currentPage: pageid, totalPages: pagecount, onPageChanged: pageClick, bootstrapMajorVersion: 3}
    else 
        $("div#content").html("暂无推荐")


$(document).ready ->
  pageClick(null, null, 1)
