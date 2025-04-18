#include <iostream>
#include <string>
#include <vector>
#include <fstream>

class Student {
protected:
	std::string first_name;
	std::string last_name;
	double gpa;
	int graduation_year;
	std::string graduation_semester;
	int enrolled_year;
	std::string enrolled_semester;
	std::string program_level; // undergrad or grad

public:
	// default constructor
	Student() 
		: first_name("Unknown"), last_name("Unknown"), gpa(0.0),
		graduation_year(0), graduation_semester("Unknown"),
		enrolled_year(0), enrolled_semester("Unknown"), program_level("Unknown") {}

	// destructor
	virtual ~Student() {}

	// getter and setter functions
	void setName(const std::string &first, const std::string &last) {
		first_name = first;
		last_name = last;
	}

	std::string getName() const {
		return first_name + " " + last_name;
	}

	void setGPA(double new_gpa) {
		gpa = new_gpa;
	}
	
	double getGPA() const {
		return gpa;
	}

	void setGraduationYear(int year) {
		graduation_year = year;
	}

	int getGraduationYear() const {
		return graduation_year;
	}

	void setGraduationSemester(const std::string &semester) {
		graduation_semester = semester;
	}

	std::string getGraduationSemester() const {
		return graduation_semester;
	}

	void setEnrolledYear(int year) {
		enrolled_year = year;
	}

	int getEnrolledYear() const {
		return enrolled_year;
	}

	void setEnrolledSemester(const std::string &semester) {
		enrolled_semester = semester;
	}

	std::string getEnrolledSemester() const {
		return enrolled_semester;
	}

	void setProgramLevel(const std::string &level) {
		program_level = level;
	}

	std::string getProgramLevel() const {
		return program_level;
	}

	// virtual function for displaying student details
	virtual void displayDetails(std::ostream &os) const {
		os << "Name: " << getName() << "\n"
		   << "GPA: " << gpa << "\n" 
		   << "Graduation Year: " << graduation_year << "\n"
		   << "Graduation Semester: " << graduation_semester << "\n"
		   << "Enrolled Year: " << enrolled_year << "\n"
		   << "Enrolled Semester: " << enrolled_semester << "\n"
		   << "Program Level: " << program_level << "\n";
	}
};

class Art_Student : public Student {
private:
	std::string art_emphasis; // art studio, art history, art education

public:
	// default constructor
	Art_Student() : art_emphasis("Unknown") {}

	// destructor
	~Art_Student() override {}

	void setArtEmphasis(const std::string &emphasis) {
		art_emphasis = emphasis;
	}

	std::string getArtEmphasis() const {
		return art_emphasis;
	}

	void displayDetails(std::ostream &os) const override {
		Student::displayDetails(os);
		os << "Art Emphasis: " << art_emphasis << "\n";
	}
};

class Physics_Student : public Student{
private:
	std::string concentration; // biophysics, earth and planetary sciences

public:
	// default constructor
	Physics_Student() : concentration("Unknown") {}

	// destructor
	~Physics_Student() override {}

	void setConcentration(const std::string &conc) {
		concentration = conc;
	}

	std::string getConcentration() const {
		return concentration;
	}

	void displayDetails(std::ostream &os) const override {
		Student::displayDetails(os);
		os << "Concentration: " << concentration << "\n";
	}
};

int main() {
	// vectors to hold pointers to students
	std::vector<Art_Student *> art_students;
	std::vector<Physics_Student *> physics_students;

	// creating and assigning to art_student objects
	int i;
	for (i = 0; i < 5; ++i) {
		auto *art_student = new Art_Student;
		art_student->setName("ArtFirst" + std::to_string(i + 1), "ArtLast" + std::to_string(i + 1));
		art_student->setGPA(3.5 + i * 0.1);
		art_student->setGraduationYear(2025);
		art_student->setGraduationSemester("Spring");
		art_student->setEnrolledYear(2021);
		art_student->setProgramLevel("Undergrad");
		art_student->setArtEmphasis("Art Studio");
		art_students.push_back(art_student);
	}

	// creating and assigning values to physics_student objects
	for (i = 0; i < 5; ++i) {
		auto *physics_student = new Physics_Student;
		physics_student->setName("PhysicsFirst" + std::to_string(i + 1), "PhysicsLast" + std::to_string(i + 1));
		physics_student->setGPA(3.8 + i * 0.05);
		physics_student->setGraduationYear(2026);
		physics_student->setGraduationSemester("Fall");
		physics_student->setEnrolledYear(2022);
		physics_student->setEnrolledSemester("Spring");
		physics_student->setProgramLevel("Grad");
		physics_student->setConcentration("Biophysics");
		physics_students.push_back(physics_student);
	}

	// writing student info to file
	std::ofstream outfile("student_info.dat", std::ios::out);
	if (outfile.is_open()) {
		outfile << "Art Students:\n";
		for (const auto &student : art_students) {
			student->displayDetails(outfile);
			outfile << "-----------------------\n";
		}

		outfile << "\nPhysics Students:\n";
		for (const auto &student : physics_students) {
			student->displayDetails(outfile);
			outfile << "-----------------------\n";
		}

		outfile.close();
		std::cout << "Student Information written to student_info.dat\n";
	} else {
		std::cerr << "Error: Could not open file for writing.\n";
	}

	// cleaning up allocated memory
	for (auto &student : art_students) {
		delete student;
	}
	art_students.clear();

	for (auto &student : physics_students) 	{
		delete student;
	}
	physics_students.clear();

	return 0;
}
