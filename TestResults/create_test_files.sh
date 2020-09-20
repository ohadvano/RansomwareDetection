#!/bin/sh





echo "#include <string>
#include <ctime>
#include <fstream>
#include <iostream>
#include <time.h>


using namespace std;
# define LOG_NAME "logfile.txt"
# define LOG_PATH "~/ohadoz/Desktop/oz_test/logfile.txt"
#define DTTMFMT "%Y-%m-%d %H:%M:%S "
#define DTTMSZ 21


// Helper function for textual date and time.
// DTTMSZ must allow extra character for the null terminator.

static char *getDtTm (char *buff) {
    time_t t = time (0);
    strftime (buff, DTTMSZ, DTTMFMT, localtime (&t));
    return buff;
}



namespace Log
{
    class Logger
    {
        public:
            char* LogPath;

            Logger(char* logPath)
            {
				if (std::ifstream(LOG_NAME))
				{
					return;
					
				}
				else
				{
					std::ofstream file{ LOG_NAME };
					LogPath = logPath;
				}
            }

            void WriteLog(string logInfo)
            {
				if (!std::ifstream(LOG_NAME))
				{
				return;			
				}
   				char buff[DTTMSZ];
				std::ofstream file;
				file.open(LOG_NAME, std::ios_base::app);
    				file << getDtTm (buff) << logInfo << endl;
				file.close();

			}

            void WriteError(string logError)
            {
				if (!std::ifstream(LOG_NAME))
				{
				return;
				}
   				char buff[DTTMSZ];
				std::ofstream file;
				file.open(LOG_NAME, std::ios_base::app);
    				file << getDtTm (buff) << "ERROR:"<<logError << endl;
				file.close();
			}
    };
}

using namespace Log;
int main(
{

	cout << "ok" << endl;
        Logger*  new_logger= new Logger(LOG_PATH);
	new_logger->WriteLog("wowwwwwwwwwwwwwwwwwww\n");
	new_logger->WriteLog("1111111111111111111111\n");
new_logger->WriteError("2222222222222222222222\n");
	return ;
}" >oz.txt











echo "#include <string>
#include <ctime>
#include <fstream>
#include <iostream>
#include <time.h>
#include <cstdlib>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/wait.h>
#include <sstream>
#include <string.h>



using namespace std;
typedef unsigned char uint8;





string SplitFilename (const string& str)
{
  size_t found;
  found=str.find_last_of("/\\");
  //return  str.substr(0,found); //folder
  return str.substr(found+1) ; //file
}




enum fuse_buf_flags {
	/**
	 * Buffer contains a file descriptor
	 *
	 * If this flag is set, the .fd field is valid, otherwise the
	 * .mem fields is valid.
	 */
	FUSE_BUF_IS_FD		= (1 << 1),

	FUSE_BUF_IS_FD_OZ		= (1 << 0)
};





namespace Heuristics
{
    class HeuristicBase
    {
        public:

/*
            string GetFilePathFromWriteAction(WriteBufAction* writeAction)
            {
                return "x";
            }

            string GetNewContent(string filePath, WriteBufAction* writeAction)
            {
                return "x";
            }





*/

            uint8* ReadFile(string filePath)
            {
		string res;
		string full_res;
		ifstream file(filePath);
		while(getline(file,res))
		{
			full_res=full_res+res;
		}
		file.close() ;
		uint8 *full_res_conv=new unsigned char[full_res.length()+1];
		strcpy((char *)full_res_conv,full_res.c_str());
		return full_res_conv;	
	    }




            int GetLength(uint8* byteStream)
            {
		return strlen((char*)byteStream);
            }






    };

}
typedef unsigned char uint8;
using namespace Heuristics;

int main()
{
	fuse_buf_flags fd;
fd = FUSE_BUF_IS_FD_OZ;
	

	cout << "ok" << endl;
        HeuristicBase*  new_HeuristicBase= new HeuristicBase();
      //  unsigned char* t = reinterpret_cast<const unsigned char *>("UCHAR TO CONST UCHAR");
//uint8* str = (unsigned char*)"oz oz oz          oz oz ";
//	int res=new_HeuristicBase->GetLength(str);
//	cout << res<< endl;
	//uint8* resu=new_HeuristicBase->ReadFile("~//ohadoz//Desktop//oz_test//testoz");
	uint8* res=new_HeuristicBase->ReadFile("/home/ohadoz/Desktop/oz_test/Log.cpp");
	int res2=new_HeuristicBase->GetLength(res);
	//string res=new_HeuristicBase->RunFileUtility("/home/ohadoz/Desktop/oz_test/test");
	//int res=new_HeuristicBase->RunSdHash("~/ohadoz/Desktop/oz_test/Logger.cpp","~/ohadoz/Desktop/oz_test/Logger2.cpp");
	//int res=new_HeuristicBase->RunSdHash("~/ohadoz/Desktop/oz_test/test","~/ohadoz/Desktop/oz_test/Makefile");
	cout << FUSE_BUF_IS_FD_OZ<< endl;
	cout << fd<< endl;
	return 0;
}
" > oz1.txt











echo "all:
	g++ -g -Wall Heuristics2.cpp -o testa" >oz2.txt














echo "Disputed articles

A 2013 study from Oxford University concluded that the most disputed articles on the English Wikipedia tended to be broader issues, while on other language Wikipedias the most disputed articles tended to be regional issues; this is due to the English language's status as a global lingua franca, which means that many who edit the English Wikipedia do not speak English as a native language.[clarification needed] The study stated that the most disputed entries on the English Wikipedia were: George W. Bush, anarchism, Muhammad, list of WWE personnel, global warming, circumcision, United States, Jesus, race and intelligence, and Christianity.[29]
Varieties of English

One controversy in the English Wikipedia concerns which national variety of the English language is to be preferred, with the most commonly advocated candidates being American English and British English.[30] Perennial suggestions range from standardizing upon a single form of English to forking the English Wikipedia project. A style guideline states, the English Wikipedia has no general preference for a major national variety of the language and an article on a topic that has strong ties to a particular English-speaking nation uses the appropriate variety of English for that nation.[31] An article should use spelling and grammar variants consistently; for example, color and colour are not to be used in the same article, since they represent American and British English, respectively. The guide also states that an article must remain in its original national variant.

There has been a similar issue in the Chinese-language Wikipedia concerning regional differences in writing. Efforts toward a language fork for Portuguese Wikipedia have failed, but those regarding Norwegian Wikipedia succeeded.

Andrew Lih wrote that the English Wikipedia "didn't have the chance to go through a debate over whether there should be a British English Wikipedia or an American English Wikipedia" because the English Wikipedia was the original edition.[32][clarification needed] Editors agreed to use U.S. spellings for primarily American topics and British spellings for primarily British topics. In 2009 Lih wrote, "No doubt, American spellings tend to dominate by default just because of sheer numbers."[33]
Wikiprojects, and assessments of articles importance and quality
Main article: WikiProject

A "WikiProject" is a group of contributors who want to work together as a team to improve Wikipedia. These groups often focus on a specific topic area (for example, womens history), a specific location or a specific kind of task (for example, checking newly created pages). The English Wikipedia currently has over 2,000 WikiProjects and activity varies.[34]

In 2007, in preparation for producing a print version, the English Wikipedia introduced an assessment scale of the quality of articles.[35] Articles are rated by WikiProjects. The range of quality classes begins with "Stub" (very short pages), followed by "Start", "C" and "B" (in increasing order of quality). Community peer review is needed for the article to enter one of the highest quality classes: either "good article", "A" or the highest, "featured article". Of the about 4.4 million articles and lists assessed as of March 2015, a little more than 5,000 (0.12%) are featured articles, and fewer than 2,000 (0.04%) are featured lists. One featured article per day, as selected by editors, appears on the main page of Wikipedia.[36][37]

The articles can also be rated as per "importance" as judged by a WikiProject. Currently, there are 5 importance categories: "low", "mid", "high", "top", and "???" for unclassified/uncertain level. For a particular article, different WikiProjects may assign different importance levels.

The Wikipedia Version 1.0 Editorial Team has developed a table (shown below) that displays data of all rated articles by quality and importance, on the English Wikipedia. If an article or list receives different ratings by two or more WikiProjects, then the highest rating is used in the table, pie-charts, and bar-chart. The software regularly auto-updates the data.

Researcher Giacomo Poderi found that articles tend to reach featured status via the intensive work of a few editors.[38] A 2010 study found unevenness in quality among featured articles and concluded that the community process is ineffective in assessing the quality of articles.">oz3.txt











echo "Los Alamos National Laboratory (Los Alamos or LANL for short) is a United States Department of Energy national laboratory initially organized during World War II for the design of nuclear weapons as part of the Manhattan Project. It is located a short distance northwest of Santa Fe, New Mexico, in the southwestern United States.

Los Alamos was selected as the top secret location for bomb design in late 1942, and officially commissioned the next year, under the management of University of California.[5] At the time it was known as Project Y and was the center for weapon design and overall coordination. Other labs, today known as Oak Ridge National Laboratory and the Hanford Site, concentrated on the production of uranium and plutonium bomb fuels. Los Alamos was the heart of the project, collecting together some of the worlds most famous scientists, among them numerous Nobel Prize winners. The site was known variously as Project Y, Los Alamos Laboratory, and Los Alamos Scientific Laboratory through this period.[6][7]

The labs existence was announced to the world in the post-WWII era, when it became known universally as Los Alamos. In 1952, the Atomic Energy Commission formed a second design lab under the direction of the University of California, Berkeley, becoming the Lawrence Livermore National Laboratory (LLNL).[8] Since that date the two labs have competed on a wide variety of bomb designs. With the ending of the Cold War, both labs turned their focus increasingly to civilian missions. Today, Los Alamos is one of the largest science and technology institutions in the world. It conducts multidisciplinary research in fields such as national security, space exploration, nuclear fusion, renewable energy,[9] medicine, nanotechnology, and supercomputing. The town of Los Alamos, New Mexico, directly north of the lab, grew extensively through this period.

After several reorganizations, LANL is currently managed and operated by Triad National Security, LLC.[6][10]
Contents

    1 History
        1.1 The Manhattan Project
        1.2 Post-war
        1.3 Post-Cold War
            1.3.1 Medical work
            1.3.2 Negative publicity
    2 Science mission
    3 Laboratory management and operations
        3.1 Contract changes
        3.2 Safety Management
    4 Extended operations
    5 Controversy and criticism
    6 Institutional statistics
    7 Directors
    8 Notable scientists
    9 See also
    10 References
    11 Further reading
    12 External links

History
The Manhattan Project
Main article: Project Y

The laboratory was founded during World War II as a secret, centralized facility to coordinate the scientific research of the Manhattan Project, the Allied project to develop the first nuclear weapons. In September 1942, the difficulties encountered in conducting preliminary studies on nuclear weapons at universities scattered across the country indicated the need for a laboratory dedicated solely to that purpose.[citation needed]

General Leslie Groves wanted a central laboratory at an isolated location for safety, and to keep the scientists away from the populace. It should be at least 200 miles from international boundaries and west of the Mississippi. Major John Dudley suggested Oak City, Utah or Jemez Springs, New Mexico but both were rejected. Jemez Springs was only a short distance from the current site. Project Y director J. Robert Oppenheimer had spent much time in his youth in the New Mexico area, and suggested the Los Alamos Ranch School on the mesa. Dudley had rejected the school as not meeting Groves’ criteria, but as soon as Groves saw it he said in effect "This is the place".[11] Oppenheimer became the laboratorys first director.

During the Manhattan Project, Los Alamos hosted thousands of employees, including many Nobel Prize-winning scientists. The location was a total secret. Its only mailing address was a post office box, number 1663, in Santa Fe, New Mexico. Eventually two other post office boxes were used, 180 and 1539, also in Santa Fe.[12] Though its contract with the University of California was initially intended to be temporary,[citation needed] the relationship was maintained long after the war. Until the atomic bombings of Hiroshima and Nagasaki, Japan, University of California president Robert Sproul did not know what the purpose of the laboratory was and thought it might be producing a "death ray".[13] The only member of the UC administration who knew its true purpose—indeed, the only one who knew its exact physical location—was the Secretary-Treasurer Robert Underhill, who was in charge of wartime contracts and liabilities.[citation needed]
The first stages of the explosion of the Trinity nuclear test.

The work of the laboratory culminated in several atomic devices, one of which was used in the first nuclear test near Alamogordo, New Mexico, codenamed "Trinity", on July 16, 1945. The other two were weapons, "Little Boy" and "Fat Man", which were used in the attacks on Hiroshima and Nagasaki. The Laboratory received the Army-Navy ‘E’ Award for Excellence in production on October 16, 1945.[citation needed]
Post-war

After the war, Oppenheimer retired from the directorship, and it was taken over by Norris Bradbury, whose initial mission was to make the previously hand-assembled atomic bombs "G.I. proof" so that they could be mass-produced and used without the assistance of highly trained scientists. Many of the original Los Alamos "luminaries" chose to leave the laboratory, and some even became outspoken opponents to the further development of nuclear weapons.[citation needed]

The name officially changed to the Los Alamos Scientific Laboratory on January 1, 1947. By this time, Argonne had already been made the first National Laboratory the previous year. Los Alamos would not become a National Laboratory in name until 1981.[14]

In the years since the 1940s, Los Alamos was responsible for the development of the hydrogen bomb, and many other variants of nuclear weapons. In 1952, Lawrence Livermore National Laboratory was founded to act as Los Alamos' "competitor", with the hope that two laboratories for the design of nuclear weapons would spur innovation. Los Alamos and Livermore served as the primary classified laboratories in the U.S. national laboratory system, designing all the country's nuclear arsenal. Additional work included basic scientific research, particle accelerator development, health physics, and fusion power research as part of Project Sherwood. Many nuclear tests were undertaken in the Marshall Islands and at the Nevada Test Site. During the late-1950s, a number of scientists including Dr. J. Robert "Bob" Beyster left Los Alamos to work for General Atomics (GA) in San Diego.[15]

Three major nuclear-related accidents have occurred at LANL. Criticality accidents occurred in August 1945 and May 1946, and a third accident occurred during an annual physical inventory in December 1958.[16]

Several buildings associated with the Manhattan Project at Los Alamos were declared a National Historic Landmark in 1965.[4][17]
Post-Cold War

At the end of the Cold War, both labs went through a process of intense scientific diversification in their research programs to adapt to the changing political conditions that no longer required as much research towards developing new nuclear weapons and has led the lab to increase research for "non-war" science and technology. Los Alamos nuclear work is currently thought to relate primarily to computer simulations and stockpile stewardship. The development of the Dual-Axis Radiographic Hydrodynamic Test Facility will allow complex simulations of nuclear tests to take place without full explosive yields.[citation needed]

The laboratory contributed to the early development of the flow cytometry technology. In the 1950s, researcher Mack Fulwyler developed a technique for sorting erythrocytes that combined the Coulter Principle of Coulter counter technologies, which measures the presence of cells and their size, with ink jet technology, which produces a laminar flow of liquid that breaks up into separate, fine drops. In 1969, Los Alamos reported the first fluorescence detector apparatus, which accurately measured the number and size of ovarian cells and blood cells.[18]

As of 2017, other research performed at the lab included developing cheaper, cleaner bio-fuels and advancing scientific understanding around renewable energy.[19]

Non-nuclear national security and defense development is also a priority at the lab. This includes preventing outbreaks of deadly diseases by improving detection tools and the monitoring the effectiveness of the United States’ vaccine distribution infrastructure. Additional advancements include the ASPECT airplane that can detect bio threats from the sky.[20]
Medical work

In 2008, development for a safer, more comfortable and accurate test for breast cancer was ongoing by scientists Lianjie Huang and Kenneth M. Hanson and collaborators. The new technique, called ultrasound-computed tomography (ultrasound CT), uses sound waves to accurately detect small tumors that traditional mammography cannot.[21]

The lab has made intense efforts for humanitarian causes through its scientific research in medicine. In 2010, three vaccines for the Human Immunodeficiency Virus were being tested by lab scientist Bette Korber and her team. "These vaccines might finally deal a lethal blow to the AIDS virus", says Chang-Shung Tung, leader of the Labs Theoretical Biology and Biophysics group.[22]
Negative publicity

The laboratory has attracted negative publicity from a number of events. In 1999, Los Alamos scientist Wen Ho Lee was accused of 59 counts of mishandling classified information by downloading nuclear secrets—"weapons codes" used for computer simulations of nuclear weapons tests—to data tapes and removing them from the lab. After ten months in jail, Lee pleaded guilty to a single count and the other 58 were dismissed with an apology from U.S. District Judge James Parker for his incarceration.[23] Lee had been suspected for having shared U.S. nuclear secrets with China, but investigators were never able to establish what Lee did with the downloaded data.[24] In 2000, two computer hard drives containing classified data were announced to have gone missing from a secure area within the laboratory, but were later found behind a photocopier. The year 2000 brought additional hardship for the laboratory in the form of the Cerro Grande Fire, a severe forest fire that destroyed several buildings (and employees homes) and forced the laboratory to close for two weeks. In 2003, the laboratorys director (John Browne) and deputy director resigned following accusations that they had improperly dismissed two whistleblowers who had alleged widespread theft at the lab.[citation needed]

In July 2004, an inventory of classified weapons data revealed that four hard disk drives were missing: two of the drives were subsequently found to have been improperly moved to a different building, but another two remained unaccounted for. In response, director Peter Nanos shut down large parts of the laboratory and publicly rebuked scientists working there for a lax attitude to security procedures. In the laboratorys August 2004 newsletter he wrote, "This willful flouting of the rules must stop, and I dont care how many people I have to fire to make it stop". Nanos is also quoted as saying, "If I have to restart the laboratory with 10 people, I will". However, a report released in January 2005 found that the drives were in fact an artifact of an inconsistent inventory system: the report concludes that 12 barcodes were issued to a group of disk drives that needed only 10, but the two surplus barcodes nevertheless appeared in inventory. Auditors incorrectly concluded that two disks were missing. The report states, "The allegedly missing disks never existed and no compromise of classified material has occurred". This incident is widely reported as contributing to continuing distrust of management at the lab. In May 2005, Nanos stepped down as director.[citation needed]
Science mission

Los Alamos National Laboratorys mission is to solve national security challenges through scientific excellence.[25] The laboratorys strategic plan reflects U.S. priorities spanning nuclear security, intelligence, defense, emergency response, nonproliferation, counterterrorism, energy security, emerging threats, and environmental management. This strategy is aligned with priorities set by the Department of Energy (DOE), the National Nuclear Security Administration (NNSA), and national strategy guidance documents, such as the Nuclear Posture Review, the National Security Strategy, and the Blueprint for a Secure Energy Future

Los Alamos is the senior laboratory in the DOE system, and executes work in all areas of the DOE mission: national security, science, energy, and environmental management.[26] The laboratory also performs work for the Department of Defense (DoD), Intelligence Community (IC), and Department of Homeland Security (DHS), among others. The laboratorys multidisciplinary scientific capabilities and activities are organized into four Science Pillars:[27]

    The Information, Science, and Technology Pillar leverages advances in theory, algorithms, and the exponential growth of high-performance computing to accelerate the integrative and predictive capability of the scientific method.
    The Materials for the Future Pillar seeks to optimize materials for national security applications by predicting and controlling their performance and functionality through discovery science and engineering.
    The Nuclear and Particle Futures Pillar applies science and technology to intransigent problems of system identification and characterization in areas of global security, nuclear defense, energy, and health.
    The Science of Signatures Pillar integrates nuclear experiments, theory, and simulation to understand and engineer complex nuclear phenomena.

Through partnerships across government agencies, laboratories, universities, and industry, Los Alamos integrates science, technology, research and development solutions to achieve the maximum impact on strategic national security priorities. To further these collaborative efforts, Los Alamos operates three main user facilities:

    The Center for Integrated Nanotechnologies: The Center for Integrated Nanotechnologies is a DOE/Office of Science National User Facility operated jointly by Sandia and Los Alamos National Laboratories with facilities at both Laboratories. CINT is dedicated to establishing the scientific principles that govern the design, performance, and integration of nanoscale materials into microscale and macroscale systems and devices.[28]
    Los Alamos Neutron Science Center (LANSCE): The Los Alamos Neutron Science Center is one of the worlds most powerful linear accelerators. LANSCE provides the scientific community with intense sources of neutrons with the capability of performing experiments supporting civilian and national security research. This facility is sponsored by the Department of Energy, the National Nuclear Security Administration, Office of Science and Office of Nuclear Energy, Science and Technology.
    The National High Magnetic Field Laboratory (NHMFL), Pulsed Field Facility: The Pulsed Field Facility at Los Alamos National Laboratory in Los Alamos, New Mexico, is one of three campuses of the National High Magnetic Field Laboratory (NHMFL), the other two being at Florida State University, Tallahassee and the University of Florida. The Pulsed Field Facility at Los Alamos National Laboratory operates an international user program for research in high magnetic fields.

As of 2017, the Los Alamos National Laboratory is using data and algorithms to possibly protect public health by tracking the growth of infectious diseases. Digital epidemiologists at the labs Information Systems and Modeling group are using clinical surveillance data, Google search queries, census data, Wikipedia, and even tweets to create a system that could predict epidemics. The team is using data from Brazil as its model; Brazil was notably threatened by the Zika virus as it prepared to host the Summer Olympics in 2016.[29]
Laboratory management and operations

Around LANLs 43-square-mile property are 2,000 dumpsites which have permanently contaminated the environment. It also contributed to thousands of dumpsites at 108 locations in 29 US states.[30]
Contract changes

Continuing efforts to make the laboratory more efficient led the Department of Energy to open its contract with the University of California to bids from other vendors in 2003. Though the university and the laboratory had difficult relations many times since their first World War II contract, this was the first time that the university ever had to compete for management of the laboratory. The University of California decided to create a private company with the Bechtel Corporation, Washington Group International, and the BWX Technologies to bid on the contract to operate the laboratory. The UC/Bechtel led corporation—Los Alamos National Security, LLC (LANS)—was pitted against a team formed by the University of Texas System partnered with Lockheed-Martin. In December 2005, the Department of Energy announced that LANS had won the next seven-year contract to manage and operate the laboratory.[citation needed]

On June 1, 2006, the University of California ended its sixty years of direct involvement in operating Los Alamos National Laboratory, and management control of the laboratory was taken over by Los Alamos National Security, LLC with effect October 1, 2007. Approximately 95% of the former 10,000 plus UC employees at LANL were rehired by LANS to continue working at LANL. Other than UC appointing three members to the eleven member board of directors that oversees LANS, UC now has virtually no responsibility or direct involvement in LANL. UC policies and regulations that apply to UC campuses and its two national laboratories in California (Lawrence Berkeley and Lawrence Livermore) no longer apply to LANL, and the LANL director no longer reports to the UC Regents or UC Office of the President. Also, LANL employees were removed from the UCs 403(b) retirement savings and defined benefits pension program and placed in a LANS run program. While the LANS retirement program provides rehired UC employees with pensions similar to those UC would have given them, LANS no longer guarantees full pensions to newly hired LANL employees. It now provides basic 401(k) retirement saving options.[citation needed]

On June 8, 2018, the NNSA announced that Triad National Security, LLC, a joint venture between Battelle Memorial Institute, the University of California, and Texas A&M University, would assume operation and management of LANL beginning November 1, 2018.[31]
Safety Management

In August 2011, a near criticality incident happened with eight rods of plutonium placed close to each other to take a photo. In the aftermath, 12 of 14 of the labs safety staff left in anger about their advice being dismissed by the management. Without safety management, the Plutonium Facility PF-4 was shut down in 2013 and is still closed in 2017 because the lab fails to meet expectations.[32] As a consequence, the U.S. Department of Energy, sought alternative suppliers the LANLs management contract.[33]

The lab was penalized with a $57 million reduction in its 2014 budget over the February 14, 2014 accident at the Waste Isolation Pilot Plant for which it was partly responsible.[34]

In August 2017, the improper storage of plutonium metal could have triggered a criticality accident, and subsequently staff failed to declare the failure as required by procedure.[33][35]
Extended operations
	
This section does not cite any sources. Please help improve this section by adding citations to reliable sources. Unsourced material may be challenged and removed. (July 2015) (Learn how and when to remove this template message)

With support of the National Science Foundation, LANL operates one of the three National High Magnetic Field Laboratories in conjunction with and located at two other sites Florida State University in Tallahassee, Florida, and University of Florida in Gainesville, Florida.

Los Alamos National Laboratory is a partner in the Joint Genome Institute (JGI) located in Walnut Creek, California. JGI was founded in 1997 to unite the expertise and resources in genome mapping, DNA sequencing, technology development, and information sciences pioneered at the three genome centers at University of Californias Lawrence Berkeley National Laboratory (LBNL), Lawrence Livermore National Laboratory (LLNL), and LANL.

The Integrated Computing Network (ICN) is a multi-security level network at the LANL integrating large host supercomputers, a file server, a batch server, a printer and graphics output server and numerous other general purpose and specialized systems. IBM Roadrunner, which was part of this network, was the first supercomputer to hit petaflop speeds.[36]

Until 1999, The Los Alamos National Laboratory hosted the arXiv e-print archive.[37] The arXiv is currently operated and funded by Cornell University.

The coreboot project was initially developed at LANL.[38]

In the recent years, the Laboratory has developed a major research program in systems biology modeling, known at LANL under the name q-bio.

Several serials are published by LANL:[39]

    National Security Science
    1663
    Community Connections
    Actinide Research Quarterly
    @theBradbury
    Physical Sciences Vistas

LANL also published Los Alamos Science from 1980 to 2005, as well as the Nuclear Weapons Journal which was replaced by National Security Science after 2 issues in 2009.
Controversy and criticism

In 2005, Congress held new hearings on lingering security issues at Los Alamos National Weapons Laboratory in New Mexico. But documented problems continued to be ignored.[40][41]

In November 2008 a drum containing nuclear waste was ruptured due to a 'deflagration' according to an inspector general report of the Dept. of Energy, which due to lab mistakes, also occurred in 2014 at the Carlsbad plant with significant disruptions and costs across the industry.[42]

In 2009, 69 computers which did not contain classified information were lost.[43] 2009 also saw a scare in which 1 kg (2.2 lb) of missing plutonium prompted a Department of Energy investigation into the laboratory. The investigation found that the "missing plutonium" was a result of miscalculation by LANLs statisticians and did not actually exist; but, the investigation did lead to heavy criticism of the laboratory by the DOE for security flaws and weaknesses that the DOE claimed to have found.[44][45]
Institutional statistics

LANL is northern New Mexicos largest institution and the largest employer with approximately 8,762 direct employees, 277 guard force, 505 contractors, 1,613 students, 1,143 unionized craft workers, and 452 post-doctural researches.[46] Additionally, there are roughly 120 DOE employees stationed at the laboratory to provide federal oversight of LANLs work and operations. Approximately one-third of the laboratorys technical staff members are physicists, one quarter are engineers, one-sixth are chemists and materials scientists, and the remainder work in mathematics and computational science, biology, geoscience, and other disciplines. Professional scientists and students also come to Los Alamos as visitors to participate in scientific projects. The staff collaborates with universities and industry in both basic and applied research to develop resources for the future. The annual budget is approximately US$2.2 billion.
Directors

    J. Robert Oppenheimer (1943–1945)
    Norris Bradbury (1945–1970)
    Harold Agnew (1970–1979)
    Donald Kerr (1979–1986)
    Siegfried S. Hecker (1986–1997)
    John C. Browne (1997–2003)
    George Peter Nanos (2003–2005)
    Robert W. Kuckuck (2005–2006)
    Michael R. Anastasio (2006–2011)
    Charles F. McMillan (2011–2017)
    Terry Wallace (2018)
    Thomas Mason (2018–present)

Notable scientists

    Stirling Colgate (1925–2013)
    Emily Willbanks (1930–2007)

See also

    Anti-nuclear movement in the United States
    Association of Los Alamos Scientists
    Bradbury Science Museum
    Chalk River Laboratories
    Clarence Max Fowler
    David Greenglass
    Ed Grothus
    Federation of American Scientists
    History of nuclear weapons
    Hydrogen Moderated Self-regulating Nuclear Power Module
    Julius and Ethel Rosenberg
    National Historic Landmarks in New Mexico
    National Register of Historic Places listings in Los Alamos County, New Mexico
    Timeline of Cox Report controversy

Timeline of nuclear weapons development" '> oz4.txt



echo "oz oz oz yes no" >oz5.txt
echo "oz ohad wow wow
wow yes no
ok">oz6.txt




echo "#include <string>
#include <ctime>
#include <fstream>
#include <iostream>
#include <time.h>


using namespace std;
# define LOG_NAME "logfile.txt"
# define LOG_PATH "~/ohadoz/Desktop/oz_test/logfile.txt"
#define DTTMFMT "%Y-%m-%d %H:%M:%S "
#define DTTMSZ 21


// Helper function for textual date and time.
// DTTMSZ must allow extra character for the null terminator.

static char *getDtTm (char *buff) {
    time_t t = time (0);
    strftime (buff, DTTMSZ, DTTMFMT, localtime (&t));
    return buff;
}



namespace Log
{
    class Logger
    {
        public:
            char* LogPath;

            Logger(char* logPath)
            {
				if (std::ifstream(LOG_NAME))
				{
					return;
					
				}
				else
				{
					std::ofstream file{ LOG_NAME };
					LogPath = logPath;
				}
            }

  
    };
}

using namespace Log;
int main(
{

	cout << "ok" << endl;
        Logger*  new_logger= new Logger(LOG_PATH);
	new_logger->WriteLog("wowwwwwwwwwwwwwwwwwww\n");
	new_logger->WriteLog("1111111111111111111111\n");
new_logger->WriteError("2222222222222222222222\n");
	return ;
}" >oz3.txt



echo "#include <string>
#include <ctime>
#include <fstream>
#include <iostream>
#include <time.h>


using namespace std;
# define LOG_NAME "logfile.txt"
# define LOG_PATH "~/ohadodhfdfbdfbdfbdbdbdfbdfbdfbdfbdfbdfbfdbd/logfile.txt"
#define DTTMFMT "%Y-%m-%d %H:%M:%S "
#define DTTMSZ 21


// Helper function for textual date and time.
// DTTMSZ must allow extra character for the null terminator.

static char *getDtTm (char *buff) {
    time_t t =fgdfvdfbdfbdbdfbdfbdfbdf0);
    strftime (buff, DTTMSZ, DTTMFMT, localtime (&t));
    return buff;
}



n
            Logger(char* logPath)
            
					
				}
				else
				{
					std::ofstream file{ LOG_NAME };
					LogPath = logPath;
				}
            }

  
    };
}

using namespace Log;
int main(
{

	cout << "ok" << endl;
        Logger*  new_logger= new Logger(LOG_PATH);
	new_logger->WriteLog("wowwwwwwwwwwwwwwwwwww\n");
	new_logger->WriteLog("1111111111111111111111\n");
new_logger->WriteError("2222222222222222222222\n");
	return ;
}" >oz7.txt




echo "#include <string>
#include <ctime>
#include <fstream>
#include <iostream>
#include <time.h>


using namespace std;
# define LOG_NAME "logfile.txt"
# define LOG_PATH "~/ohadodhfdfbdfbdfbdbdbdfbdfbdfbdfbdfbdfbfdbd/logfile.txt"
#define DTTMFMT "%Y-%m-%d %H:%M:%S "
#define DTTMSZ 21


// Helper function for textual date and time.
// DTTMSZ must allow extra character for the null terminator.

static char *getDtTm (char *buff) {
    time_t t =fgdfvdfbdfbdbdfbdfbdfbdf0);
    strftime (buff, DTTMSZ, dfgwfegrtgwrgbw, localtime (&t));
    return buff;
}



n
            Logger(char* logPath)
            
					
				}
				else
				{
					
					LogPath = logPath;
				}
            }

  
    };
}

using namespace Log;
int main(
{

	cout << "ok" << endl;
        Logger*  new_logger= new Logger(LOG_PATH);
fvfdbsfdbfgbg
	new_logger->WriteLog("dfgdhdfbdf\n");
new_logger->WriteError("43534534534\n");
	return ;
}" >oz8.txt



echo "#include <>
#include <kmlkmkklkllklklklkllklkkllmk>
#include <2232323>
dvsdvsd
#include <dvdvsdvsdv.h>


using namespace std;
# define sdfsdfsd "ofwosdfosdcfsd.txt"
# define LOG_PATH "~/ohadodhfdfbdfbdfbdbdbdfbdfbdfbdfbdfbdfbfdbd/logfile.txt"
#define DTTMFMT "%Y-%m-%d %H:%M:%S "
#definjnjnjnjnjnjnne DTTMSZ 21


// Helper function for textual date and time.


static char *iniknknjnj (char *buff) {
    time_t t =fgdfvdfbdfbdbdfbdfbdfbdf0);
    strftime (buff, DTTMSZ, dfgwfegrtgwrgbw, localtime (&t));
    return buff;
}



n
            Logger(char* logPath)
            
					
				}
				else
				{
					
					LogPath = cascadcad;
				}
            }

  
    };
}

using  mkmkmk;
inddddt maisdfsdn(
{

	cout << "ok" << endl;
        Logger*  new_logger= new Logger(LOG_PATH);
fvfdbsfdbfgbg
	new_logger->WriteLog("dfgdhdfbdf\n");
new_logger->\("43534534534\n");
	 ;
}" >oz9.txt



echo "#include <string>
#include <ctime>
#include <fstream>
#include <iostream>
#include <time.h>


using namespace std;
# define LOG_NAME "logfile.txt"
# define LOG_PATH "~/ohadodhfdfbdfbdfbdbdbdfbdfbdfbdfbdfbdfbfdbd/logfile.txt"
#define DTTMFMT "%Y-%m-%d %H:%M:%S "
#define DTTMSZ 21


// Helper function for textual date and time.
// DTTMSZ must allow extra character for the null terminator.

static char *getDtTm (char *buff) {
    time_t t =fgdfvdfbdfbdbdfbdfbdfbdf0);
    strftime (buff, DTTMSZ, dfgwfegrtgwrgbw, localtime (&t));
    return buff;
}



n
            Logger(char* logPath)
            
					
				}
				else
				{
					
					LogPath = logPath;
				}
            }

  
    };
}

using namespace Log;
int main(
{

	cout << "ok" << endl;
        Logger*  new_logger= new Logger(LOG_PATH);
fvfdbsfdbfgbg
	new_logger->WriteLog("dfgdhdfbdf\n");
new_logger->WriteError("43534534534\n");
	return ;
}" >oz10.cpp











