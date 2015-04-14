protocol ExampleProtocol
{
    var simpleDescription:String
    {
        get
    }
    mutating func adjust()
}
//类继承了接口
class SimpleClass:ExampleProtocol
{
	var simpleDescription:String = "A very simple class"
	var anotherProperty:Int = 69015
	func adjust()
	{
		simpleDescription += "Now 100% adjusted"
	}
}

var a = SimpleClass()
a.adjust()

let aDescription = a.simpleDescription
// 结构体继承了接口
struct SimpleStructure:ExampleProtocol
{
	var simpleDescription:String = "A simple Simple Structure"
	mutating func adjust()
	{
		simpleDescription += "(adjusted)"
	}
}

var b = SimpleStructure()
b.adjust()
let bDescription = b.simpleDescription

extension Int:ExampleProtocol
{
	var simleDescription:String
	{
		return "The number \(self)"
	}
	mutating func adjust()
	{
		self += 42
	}
}