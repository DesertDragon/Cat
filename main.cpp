int main()
{
	auto cat = new Cat("Bob");
	View view(cout, cat);
	view.show();
}