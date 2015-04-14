var someList:[String] = [String]()

printfln(someList.count);

if someList.isEmpty
{
	printfln("Empty")
}
else
{
	printfln("Not Empty")
}

someList:append("Hello")
printfln(someList.count);
var tmp = someList[0]
printfln(tmp)

someList[0] = "Hello world"
someList[1] = "Hello world"//error
someList[2] = "Hello world"//out of range
//使用append追加数据
someList[0...1] = "Hello"