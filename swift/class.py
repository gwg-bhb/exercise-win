class NamedShape
{
	var numberOfSides:Int = 0
	var name:String init(name:String)
	{
		self.name = name
	}
	func simpleDescription() -> String
	{
		return "Hello \(name), A sharp with \(numberOfSides) sides"
	}
}

class Square:NamedShape
{
	var sideLength:Double init(sideLength:Double, name:String)
	{
		self.sideLength = sideLength
		super.init(name:name)
		numberOfSides = 4
	}

	func area()->Double
	{
	return sideLength *sideLength
	}

	override func simpleDescription() -> String
	{
		return "A Square with sides of length \(sideLength)"
	}
}

	let test = Square(sideLength:5.2, name:"my test")
	test.area()
	test.simpleDescription()
	
