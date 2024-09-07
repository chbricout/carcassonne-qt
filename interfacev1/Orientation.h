#pragma once
#include <iostream>

enum class Orientation {
	Nord,
	Sud,
	Est,
	Ouest,
	Aucune
};

inline std::ostream& operator<<(std::ostream& f, const Orientation o) {
	switch (o)
	{
	case Orientation::Nord:
		f << "Nord";
		break;
	case Orientation::Sud:
		f << "Sud";
		break;
	case Orientation::Est:
		f << "Est";
		break;
	case Orientation::Ouest:
		f << "Ouest";
		break;
	case Orientation::Aucune:
		f << "Aucune";
		break;
	default:
		break;
	}
	return f;
}

inline std::string orientationToString(const Orientation o){
    switch (o)
    {
    case Orientation::Nord:
        return  "Nord";
        break;
    case Orientation::Sud:
        return "Sud";
        break;
    case Orientation::Est:
        return "Est";
        break;
    case Orientation::Ouest:
        return "Ouest";
        break;
    case Orientation::Aucune:
        return "Aucune";
        break;
    default:
        break;
    }
}

inline bool areOpposed(Orientation o1, Orientation o2) {
	return (o1 == Orientation::Nord && o2 == Orientation::Sud) || (o1 == Orientation::Sud && o2 == Orientation::Nord) || (o1 == Orientation::Est && o2 == Orientation::Ouest) || (o1 == Orientation::Ouest && o2 == Orientation::Est);
}
