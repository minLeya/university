//#include "SetPreservation.h"
//
//#include <iostream>
//#include <sstream>
//#include <unordered_set>
//
//std::unordered_set<int> getUserSet(int numberOfValues)
//{
//    std::unordered_set<int> set{};
//    while (true)
//    {
//        std::cout << "enter values for the E set: ";
//        std::string input{};
//        std::getline(std::cin, input);
//        std::istringstream stream{ input };
//
//        int number{};
//        bool inserted{ true };
//        while (stream >> number && inserted)
//        {
//            inserted = set.insert(number).second;
//            if (!inserted)
//                std::cout << "\nthe E set cannot have identical values\n";
//        }
//
//        if (setHasProperValues(set, numberOfValues) && inserted)
//            break;
//        else
//            set.clear();
//    }
//
//    return set;
//}
//
//bool setHasProperValues(const std::unordered_set<int>& set, int numberOfValues)
//{
//    for (const auto& element : set)
//    {
//        if (element < 0 || element > numberOfValues - 1)
//        {
//            std::cout << "\nset elements must be values between 0 and " << numberOfValues - 1
//                << " inclusive\n";
//            return false;
//        }
//    }
//
//    return true;
//}
//
////k, n
//void checkForSetPreservation(const std::vector<int>& values, int numberOfValues, int numberOfVariables)
//{
//    std::unordered_set<int> set{ getUserSet(numberOfValues) };
//    bool preservesTheSet{ true };
//
//    if (numberOfVariables == 1)
//    {
//        for (std::size_t i{ 0 }; i < values.size(); ++i)
//        {
//            //if(values[i] == )
//            /*    preservesTheSet = true;
//                break;*/
//
//            if (set.find(values[i]) == set.end())
//            {
//                preservesTheSet = false;
//                break;
//            }
//        }
//        if (preservesTheSet)
//        {
//
//        }
//    }
//
//    
//
//    if (preservesTheSet)
//        std::cout << "the function preserves the E set\n";
//    else
//        std::cout << "the function doesn't preserve the E set\n";
//}
