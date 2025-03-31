# Internal Transition  

[![Build and Test](https://github.com/Myoldmopar/InternalTransition/actions/workflows/test_pull_requests.yml/badge.svg)](https://github.com/Myoldmopar/InternalTransition/actions/workflows/test_pull_requests.yml)

Just a quick repo set up to see what things would look like if we pulled file transition into EnergyPlus itself, and stopped providing Fortran-based utilities.

## Basic Idea

Starting with EnergyPlus 25.2 input syntax, every EnergyPlus version moving forward would be able to read back to 25.1.
So 25.2 can read 25.1 and 25.2.  
And 26.1 can read 25.1, 25.2, and 26.1.

## But how?

Internally when EnergyPlus launches now, it reads the IDF, or EpJSON input file, and converts it into an nlohmann::json instance.
Right now it validates the version matches the current version of EnergyPlus, and tries to run.
What I am proposing is that we keep the transition rules moving forward inside of EnergyPlus.
If the user file is an older version, we apply a transformation to the internal EpJSON instance to bring it up to the current version, and run it.
With command line flags, we can decide whether to create an updated input file, any intermediate input files, as well as an option to just convert and exit without running.

## Why?

Users have long complained about the rapidly changing EnergyPlus input structure.
I have always considered the solution to be improved transition utilities, so over time I (and others) have made attempts to recreate transition in Python.
But after thinking it through, the very best outcome would be a much more tightly coupled transition process.
EnergyPlus developers are already providing transition utilities that intelligently create updated files, but since these rules live in the Fortran code, they are highly detached from the rest of the EnergyPlus code.

Also, we have only minimal testing in place for the auxiliary transition utilities.
By bringing it into EnergyPlus, we could gain the benefit of our established unit test framework, greatly enhancing the testability and robustness of the transition process.

As an aside - in the future, when we only have JSON input, this process will just get easier and easier, when we don't need to manage IDF inputs anymore.

I imagine the process of transitioning files could be tremendously faster.
However, file transition is usually not a frequently performed operation, so that shouldn't matter too much.

## Any issues?

We would need to think about how our transition workflows operate.
Right now they are generally based on finding all the transition binaries and running things in a sequence.
In this case, that process would be embedded within EnergyPlus, so it would be a simpler process from 25.1 and beyond.

The transition workflow does not only manipulate fields each version, it also updates report variables in various known objects.
This process will need to be included in the EnergyPlus implementation.

If we are converting EpJSON internally, but the user provided an IDF and wanted an updated IDF, we would need to decide what to do.
 - Option 1 is we can just use ConvertInputFormat to produce the IDF back to the user. The risk is that comments would be now missing (I think!?).
 - Option 2 we can just report out EpJSON transitioned files.  This will help guide users to using EpJSON. 
 - Option 3 is the most aggressive, in which we only even try to convert EpJSON input files.  This is the strictest way to make sure we get users over to EpJSON.  It could be justified, however, because of how our convert-back-to-IDF process will indeed lead to a stripped clean IDF with no user comments.

One other issue is that the version updater code will validate each input file version against the IDD at that point.
We would need to discuss what to do here.
We could embed the schema for each version inside EnergyPlus, like we do now for the current version.
That may be overkill, but I'm not currently sure.

Transition binaries accept list files, which include a list of IDFs to convert.
I think it might be awkward to try to support that with EnergyPlus, but I think it would be very easy for someone to loop over all their known files and run `energyplus --convert-only $IDF` or whatever.
