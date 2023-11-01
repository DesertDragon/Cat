void View::show(/*Cat& cat*/)
{
	//out << "Cat name: " << cat.name << " leftEye: "<< cat.leftEye << " rightEye: "<< cat.rightEye << endl;
	//out << "Cat name: " << cat.getName() << " leftEye: "<< cat.getLeftEye() << " rightEye: " << cat.getRightEye() << endl;
	//obj->show(out);
	out << objType << ": " << obj << endl; for( auto& v: views ){ v(obj, out); out << endl; }
}